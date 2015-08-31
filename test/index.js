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

    it("username", function() {
        var username = execToString("id -u -n");

        var shellUid = execToVal("id -u");
        var libUsername = userid.username(shellUid);

        libUsername.should.equal(username);
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

    it("gids", function() {
        var username = execToString("id -u -n");

        var shellGids = execToString("id -G").split(" "); //array of strings
        var libGids = userid.gids(username);

        libGids.length.should.equal(shellGids.length);

        for(var x in shellGids) 
            (~libGids.indexOf(shellGids[x] >> 0)).should.not.equal(0); //~-1 = 0
        
    });
});
