let pattern = /y/g;
pattern.lastIndex = 3;
let match = pattern.exec("xyzzy");
console.log("sticky \'/y\' only matches pattern at the lastIndex position");
console.log(match.index);
console.log(pattern.lastIndex);

console.log("");
console.log("This example specifically illustrates the sticky vs. global selections");
let global = /abc/g;
console.log(global.exec("xyz abc"));
let sticky = /abc/y;
console.log(sticky.exec("xyz abc"));

console.log("Multiple matches in a word with global option");
console.log("Banana".match(/an/g));

console.log("");
console.log("Looping over matches");
let input  = "A string with 3 numbers in it... 42 and 88.";
let number = /\b\d+\b/g;
let matchit;
while( matchit = number.exec(input)) {
    console.log("Found", matchit[0], "at", matchit.index);
}
