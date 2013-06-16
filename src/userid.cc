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

using namespace node;
using namespace v8;

Handle<Value> Uid(const Arguments& args);
Handle<Value> UserName(const Arguments& args);
Handle<Value> GroupName(const Arguments& args);
Handle<Value> Gid(const Arguments& args);

void Init(Handle<Object> target)
{
  HandleScope scope;
  target->Set(String::NewSymbol("uid"), FunctionTemplate::New(Uid)->GetFunction());
  target->Set(String::NewSymbol("username"), FunctionTemplate::New(UserName)->GetFunction());
  target->Set(String::NewSymbol("gid"), FunctionTemplate::New(Gid)->GetFunction());
  target->Set(String::NewSymbol("groupname"), FunctionTemplate::New(GroupName)->GetFunction());
};

Handle<Value> GroupName(const Arguments& args)
{
  HandleScope scope;
  struct group *group = NULL;

  if (args.Length() > 0 && args[0]->IsInt32()) {
    group = getgrgid(args[0]->Int32Value());
  } else {
    return ThrowException(Exception::Error(String::New("you must supply the gid")));
  }

  if (group) {
    return scope.Close(String::New(group->gr_name));
  } else {
    return ThrowException(Exception::Error(String::New("gid not found")));
  } 
}

Handle<Value> Gid(const Arguments& args)
{
  HandleScope scope;
  struct group *group = NULL;

  if (args.Length() > 0 && args[0]->IsString()) {
    String::Utf8Value utfname(args[0]->ToString());
    group = getgrnam(*utfname);
  } else {
    return ThrowException(Exception::Error(String::New("you must supply the groupname")));
  }


  if (group) {
    return scope.Close(Number::New(group->gr_gid));
  } else {
    return ThrowException(Exception::Error(String::New("groupname not found")));
  } 
}



Handle<Value> UserName(const Arguments& args)
{
  HandleScope scope;
  struct passwd *user = NULL;

  if (args.Length() > 0 && args[0]->IsInt32()) {
    user = getpwuid(args[0]->Int32Value());
  } else {
    return ThrowException(Exception::Error(String::New("you must supply the uid")));
  }


  if (user) {
    return scope.Close(String::New(user->pw_name));
  } else {
    return ThrowException(Exception::Error(String::New("uid not found")));
  } 
}

Handle<Value> Uid(const Arguments& args)
{
  HandleScope scope;
  struct passwd *user = NULL;

  if (args.Length() > 0 && args[0]->IsString()) {
    String::Utf8Value utfname(args[0]->ToString());
    user = getpwnam(*utfname);
  } else {
    return ThrowException(Exception::Error(String::New("you must supply the username")));
  }


  if (user) {
    Local<Object> obj = Object::New();
    obj->Set(String::New("uid"), Number::New(user->pw_uid));
    obj->Set(String::New("gid"), Number::New(user->pw_gid));
    return scope.Close(obj);
  } else {
    fprintf(stderr, "Error: %s\n", strerror(errno));
    return ThrowException(Exception::Error(String::New("username not found")));
  } 
}


extern "C" {
  static void init (Handle<Object> target)
  {
    Init(target);
  }

  NODE_MODULE(userid, init);
}
