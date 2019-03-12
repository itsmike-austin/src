let object1 = {value: 10};
let object2 = object1;
let object3 = {value: 10};

console.log("object2 = object1");
console.log("object3 has the same value as object1");

console.log("object1 == object2");
console.log(object1 == object2);

console.log("object1 == object3");
console.log(object1 == object3);

object1.value = 15;
console.log("object1.value = 15");
console.log("object2.value: " + object2.value);
console.log("object3.value: " + object3.value);
