let day1 = {
    squirrel: false,
    events: ["work", "touched tree", "pizza", "running"]
};

console.log("Data: day1.squirrel:             " + day1.squirrel);
console.log("Data: day1.wolf:                 " + day1.wolf);
day1.wolf = false;
console.log("Data: created day1.wolf = false: " + day1.wolf);

console.log("");

let anObject = {left: 1, right: 2};
console.log("anObject has left and right: left = " + anObject.left);
delete anObject.left;
console.log("anObject.left has been deleted:     " + anObject.left);
console.log("left" in anObject);
console.log("right" in anObject);

console.log("");

console.log("Object.keys of [x:, y:, z:] = " + Object.keys({x:0, y:0, z:2}));

console.log("");

let objectA = {a: 1, b: 2};
console.log("let objectA = {a: 1,b: 2};");
console.log(objectA);
Object.assign(objectA, {b: 3, c: 4});
console.log("objectA extended using Object.assign(objectA, {b:3,c:4})");
console.log(objectA);

console.log("");

let journal = [
    {events: ["work","touched tree","pizza","running","television"],
     squirrel: false},
    {events: ["work", "ice cream", "cauliflower", "lasagna", "touched tree", "brushed teeth"],
     squirrel: false},
    {events: ["weekend", "cycling", "break", "peanuts", "beer"],
     squirrel: true},
];

console.log("Dumping an array of objects");
console.log(journal);
