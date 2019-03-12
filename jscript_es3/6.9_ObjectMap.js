let ages = {
    Boris: 39,
    Liang: 22,
    Julia: 62
};

console.log(`Julia is ${ages["Julia"]}`);
console.log("Is Jack's age known?", "Jack" in ages);
console.log("Is toString's age known?", "toString" in ages);

let newAges = new Map();
newAges.set("Boris",39);
newAges.set("Liang",22);
newAges.set("Julia",62);

console.log(`Julia is ${newAges.get("Julia")}`);
console.log("Is Jack's age known?", newAges.has("Jack"));
console.log("newAges.toString exists? ", newAges.has("toString"));
