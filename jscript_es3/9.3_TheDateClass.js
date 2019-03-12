console.log("Date(): " + new Date());
console.log(new Date(2009, 11, 9));
console.log(new Date(2009, 11, 9, 12, 59, 59, 999));
console.log(new Date(2013,11,19).getTime());
console.log(new Date(1387407600000));

function getDate(string) {
    let [_, month, day, year] =
	/(\d{1,2})-(\d{1,2})-(\d{4})/.exec(string);
    return new Date(year, month-1, day);
}

console.log(getDate("1-30-2003"));
console.log("A caret (^) matches the beginning of a string");
console.log(/cat/.test("concatenate"));
console.log("A \\b says must start on a word boundary");
console.log(/\bcat\b/.test("concatenate"));
console.log("");
console.log("Choice Patterns: like \\b\\d+ (pig|cow|chicken)s?\\b");
let animalCount = /\b\d+ (pig|cow|chicken)s?\b/;
console.log(animalCount.test("15 pigs"));
console.log(animalCount.test("15 pigchickens"));
