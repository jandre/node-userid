var path = require('path');
var _userid = require(path.join(__dirname, '../build/Release/userid.node'));

/**
 * Get uid and gid for user.
 *
 * @param {String} username - username
 *
 * @return {Object} object with uid and gid, e.g. { uid: 1, gid: 2 } 
 *
 */
exports.ids = function(username) {
  return _userid.uid(username); 
};

/**
 * Get uid for user.
 *
 * @param {String} username - username in /etc/passwd
 *
 * @return {Integer} uid 
 *
 */
exports.uid = function(username) {
  var user = _userid.uid(username); 
  return user.uid;
};


/**
 * Get gid for groupname 
 *
 * @param {String} groupname - name of group in /etc/group
 *
 * @return {Integer} gid 
 *
 */
exports.gid = function(groupname) {
  return _userid.gid(groupname); 
};

/**
 * Get group name for gid 
 *
 * @param {Integer} gid - group id 
 *
 * @return {String} groupname - name of group in /etc/group
 */
exports.groupname = function(gid) {
  return _userid.groupname(gid); 
};

/**
 * Get user name for uid 
 *
 * @param {Integer} uid - user id 
 *
 * @return {String} username - name of user in /etc/passwd 
 */
exports.username = function(uid) {
 return _userid.username(uid); 
};






