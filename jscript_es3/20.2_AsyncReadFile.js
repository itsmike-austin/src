const {readFile} = require("fs").promises;
readFile("data.txt","utf8").then(text => console.log("The file contains: ",text));
