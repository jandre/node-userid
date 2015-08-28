var should = require("should");
var userid = require("../lib/userid.js");
var execSync = require("child_process").execSync;

describe("userid", function() {
    it("ids", function() {
        var username = execSync("id -u -n").toString().replace('\n', '');

        var shellUid = execSync("id -u") >> 0;
        var shellGid = execSync("id -g") >> 0;

        var libIds = userid.ids(username);

        libIds.uid.should.equal(shellUid)
        libIds.gid.should.equal(shellGid)
    });
});
