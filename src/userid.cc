/* This code is PUBLIC DOMAIN, and is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND. See the accompanying
 * LICENSE file.
 */

#include <sys/types.h>
#include <grp.h>
#include <pwd.h>

#include <nan.h>

using v8::FunctionTemplate;
using v8::Local;
using v8::Array;
using v8::String;
using v8::Number;
using v8::Object;

NAN_METHOD(Uid);
NAN_METHOD(UserName);
NAN_METHOD(GroupName);
NAN_METHOD(Gid);
NAN_METHOD(Gids);
NAN_METHOD(GroupList);

NAN_MODULE_INIT(Init)
{
  Nan::Set(target, Nan::New("uid").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(Uid)).ToLocalChecked());
  Nan::Set(target, Nan::New("username").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(UserName)).ToLocalChecked());
  Nan::Set(target, Nan::New("gid").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(Gid)).ToLocalChecked());
  Nan::Set(target, Nan::New("gids").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(Gids)).ToLocalChecked());
  Nan::Set(target, Nan::New("groupname").ToLocalChecked(),
           Nan::GetFunction(Nan::New<FunctionTemplate>(
                              GroupName)).ToLocalChecked());
}

NAN_METHOD(GroupName)
{
  struct group *group = NULL;

  if ((info.Length() > 0) && info[0]->IsInt32()) {
    group = getgrgid(info[0]->Int32Value());
  } else {
    return Nan::ThrowError("you must supply the gid");
  }

  if (group) {
    info.GetReturnValue().Set(Nan::New(group->gr_name).ToLocalChecked());
  } else {
    return Nan::ThrowError("gid not found");
  }
}

NAN_METHOD(Gids)
{
  int j, ngroups = 4;

#ifdef __APPLE__
  int *groups;
#else // ifdef __APPLE__
  gid_t *groups;
#endif // ifdef __APPLE__
  struct passwd *pw;
  Local<Array>   jsGroups = Nan::New<Array>();

  if (!((info.Length() > 0) && info[0]->IsString())) {
    return Nan::ThrowError("you must supply the groupname");
  }

  String::Utf8Value utfname(info[0]->ToString());
#ifdef __APPLE__
  groups = new int[ngroups];   // malloc(ngroups * sizeof(gid_t));
#else // ifdef __APPLE__
  groups = new gid_t[ngroups]; // malloc(ngroups * sizeof(gid_t));
#endif // ifdef __APPLE__

  if (groups == NULL) {
    return Nan::ThrowError("generating groups: ");
  }

  pw = getpwnam(*utfname);

  if (pw == NULL) {
    return Nan::ThrowError("getpwnam");
  }

  if (getgrouplist(*utfname, pw->pw_gid, groups, &ngroups) == -1) {
    delete[] groups;
#ifdef __APPLE__
    groups = new int[ngroups];
#else // ifdef __APPLE__
    groups = new gid_t[ngroups];
#endif // ifdef __APPLE__

    if (getgrouplist(*utfname, pw->pw_gid, groups, &ngroups) == -1) {
      return Nan::ThrowError("getgrouplist");
    }
  }

  for (j = 0; j < ngroups; j++) {
    Nan::Set(jsGroups, j, Nan::New(groups[j]));
  }

  delete[] groups;
  info.GetReturnValue().Set(jsGroups);
}

NAN_METHOD(Gid)
{
  struct group *group = NULL;

  if ((info.Length() > 0) && info[0]->IsString()) {
    String::Utf8Value utfname(info[0]->ToString());
    group = getgrnam(*utfname);
  } else {
    return Nan::ThrowError("you must supply the groupname");
  }


  if (group) {
    info.GetReturnValue().Set(group->gr_gid);
  } else {
    return Nan::ThrowError("groupname not found");
  }
}

NAN_METHOD(UserName)
{
  struct passwd *user = NULL;

  if ((info.Length() > 0) && info[0]->IsInt32()) {
    user = getpwuid(info[0]->Int32Value());
  } else {
    return Nan::ThrowError("you must supply the uid");
  }


  if (user) {
    info.GetReturnValue().Set(Nan::New(user->pw_name).ToLocalChecked());
  } else {
    return Nan::ThrowError("uid not found");
  }
}

NAN_METHOD(Uid)
{
  struct passwd *user = NULL;

  if ((info.Length() > 0) && info[0]->IsString()) {
    String::Utf8Value utfname(info[0]->ToString());
    user = getpwnam(*utfname);
  } else {
    return Nan::ThrowError("you must supply the username");
  }


  if (user) {
    Local<Object> obj = Nan::New<Object>();

    Nan::Set(obj, Nan::New("uid").ToLocalChecked(), Nan::New(user->pw_uid));
    Nan::Set(obj, Nan::New("gid").ToLocalChecked(), Nan::New(user->pw_gid));

    info.GetReturnValue().Set(obj);
  } else {
    return Nan::ThrowError("username not found");
  }
}

NODE_MODULE(userid, Init);
