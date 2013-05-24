# userid 

Simple nodejs library with native bindings for getting uid and gid information.  

## Installation

```
$ npm install userid 
 ```

This relies on GNU getgrname, getgrid, etc and works on POSIX systems only.  Sorry, windows.

## Usage

### Example

```js

var userid = require('userid');

// get user id
console.log("root's uid is:", userid.uid("root"));

// get group id
console.log("wheel's gid is:", userid.gid("wheel"));

// get user name
console.log("uid 0 name is:", userid.username(0));

// get group name 
console.log("gid 0 name is:", userid.groupname(0));

```

## License

Copyright (C) 2013 Jen Andre <jandre@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.


