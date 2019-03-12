function wrapValue(n) {
    let local = n;
    console.log("local in wrap value: " + local);
    return () => local;
}

console.log("local from wrapValue(3): " + wrapValue(3));

let wrap1 = wrapValue(1);
let wrap2 = wrapValue(2);
console.log("Executed method: let wrap1 = wrapValue(1): " + wrap1());
console.log("Executed method: let wrap2 = wrapValue(2): " + wrap2());
console.log("Dynamically executed function constructor");

console.log("");

function multiplier(factor) {
    return number => number * factor;
}

let twice = multiplier(2);
console.log("Twice is a dynamic method: " + twice + ", executed as twice(5): " + twice(5));

console.log("");

