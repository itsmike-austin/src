let object = Object.freeze({value: 5});
object.value = 10;
console.log("Original value of 5 was frozen and then changed to 10");
console.log(object.value);
