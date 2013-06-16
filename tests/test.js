
var userid = require('../lib/userid.js');

console.log(userid.username(0));
console.log(userid.uid("root"));
console.log(userid.gid("wheel"));
console.log(userid.groupname(20));
console.log(userid.username(1));
