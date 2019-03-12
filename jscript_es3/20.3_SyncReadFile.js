const {readFileSync} = require("fs");
console.log("The file contains: ",readFileSync("data.txt","utf8"));
