/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying 
 * LICENSE file.
 */

#include <v8.h>
#include <node.h>
#include <sys/types.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <nan.h>

using namespace v8;
using namespace node;

NAN_METHOD(Uid);
NAN_METHOD(UserName);
NAN_METHOD(GroupName);
NAN_METHOD(Gid);

void Init(Handle<Object> target)
{
  NanScope();
  target->Set(NanNew<String>("uid"), NanNew<FunctionTemplate>(Uid)->GetFunction());
  target->Set(NanNew<String>("username"), NanNew<FunctionTemplate>(UserName)->GetFunction());
  target->Set(NanNew<String>("gid"), NanNew<FunctionTemplate>(Gid)->GetFunction());
  target->Set(NanNew<String>("groupname"), NanNew<FunctionTemplate>(GroupName)->GetFunction());
};

NAN_METHOD(GroupName)
{
  NanScope();
  struct group *group = NULL;

  if (args.Length() > 0 && args[0]->IsInt32()) {
    group = getgrgid(args[0]->Int32Value());
  } else {
    NanThrowError("you must supply the gid");
  }

  if (group) {
    NanReturnValue(NanNew<String>(group->gr_name));
  } else {
    NanThrowError("gid not found");
  } 
}

NAN_METHOD(Gid)
{
  NanScope();
  struct group *group = NULL;

  if (args.Length() > 0 && args[0]->IsString()) {
    String::Utf8Value utfname(args[0]->ToString());
    group = getgrnam(*utfname);
  } else {
    NanThrowError("you must supply the groupname");
  }


  if (group) {
    NanReturnValue(NanNew<Integer>(group->gr_gid));
  } else {
    NanThrowError("groupname not found");
  } 
}



NAN_METHOD(UserName)
{
  NanScope();
  struct passwd *user = NULL;

  if (args.Length() > 0 && args[0]->IsInt32()) {
    user = getpwuid(args[0]->Int32Value());
  } else {
    NanThrowError("you must supply the uid");
  }


  if (user) {
    NanReturnValue(NanNew<String>(user->pw_name));
  } else {
    NanThrowError("uid not found");
  } 
}

NAN_METHOD(Uid)
{
  NanScope();
  struct passwd *user = NULL;

  if (args.Length() > 0 && args[0]->IsString()) {
    String::Utf8Value utfname(args[0]->ToString());
    user = getpwnam(*utfname);
  } else {
    NanThrowError("you must supply the username");
  }


  if (user ) {
    v8::Local<v8::Object> obj = NanNew<Object>();
    obj->Set(NanNew<String>("uid"), NanNew<Number>(user->pw_uid));
    obj->Set(NanNew<String>("gid"), NanNew<Number>(user->pw_gid));
   
    NanReturnValue(obj);
  } else {
    //fprintf(stderr, "Error: %s\n", strerror(errno));
    NanThrowError("username not found");
  } 
}


extern "C" {
  static void init (Handle<Object> target)
  {
    Init(target);
  }

  NODE_MODULE(userid, init);
}
