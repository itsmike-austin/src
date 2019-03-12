let {readFile} = require("fs");

readFile("data.txt","utf8",(error,text) => {
    if ( error ) throw error;
    console.log("The file contains: ", text);
});

readFile("data.txt",(error,buffer) => {
    if ( error ) throw error;
    console.log("The file contained ", buffer.length, " bytes.","The first byte is: ",buffer[0]);
});

const {writeFile} = require("fs");
writeFile("graffiti.txt","Node was here.\n",err => {
    if ( err ) console.log(`Failed to write file: ${err}`);
    else console.log("File written.");
});
