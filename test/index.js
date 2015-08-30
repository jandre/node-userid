var should = require("should");
var userid = require("../lib/userid.js");
var execSync = require("child_process").execSync;

var execToString = function(command) {
    return execSync(command).toString().replace('\n', '');
}

var execToVal = function(command) {
    return execSync(command) >> 0;
}

describe("userid", function() {
    it("ids", function() {
        var username = execToString("id -u -n");

        var shellUid = execToVal("id -u");
        var shellGid = execToVal("id -g");

        var libIds = userid.ids(username);

        libIds.uid.should.equal(shellUid)
        libIds.gid.should.equal(shellGid)
    });

    it("uid", function() {
        var username = execToString("id -u -n");

        var shellUid = execToVal("id -u");
        var libUid = userid.uid(username);

        libUid.should.equal(shellUid);
    });

    it("gid", function() {
        var shellGid = execToVal("id -g");

        var groupName = execToString("getent group " + shellGid + " | cut -d: -f1");
        var libGid = userid.gid(groupName)
        
        libGid.should.equal(shellGid);
    });

    it("groupname", function() {
        var shellGid = execToVal("id -g");

        var groupName = execToString("getent group " + shellGid + " | cut -d: -f1");
        var libGroupName = userid.groupname(shellGid);
        
        libGroupName.should.equal(groupName);
    });
});
