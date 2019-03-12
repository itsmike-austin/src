console.log("Replament Method (.replace), replace p with m in papa");
console.log("papa".replace("p","m"));
console.log("");
console.log("Pattern Replacement Method: .replace(/[ou]/,\"a\"");
console.log("Borobudur".replace(/[ou]/,"a"));
console.log("Borobudur".replace(/[ou]/g,"a"));
console.log("");
let aString = "Liskov, Barbara\nMcCarthy, John\nWadler, Philip";
console.log(aString.replace(/(\w+), (\w+)/g,"$2 $1"));
console.log("");
console.log("Pattern replacement using a function");
let s = "the cia and the fbi";
console.log("Original String: " + s);
console.log(s.replace(/\b(fbi|cia)\b/g,str => str.toUpperCase()));
console.log("A More Interesting One");
let stock = "1 lemon, 2 cabbages, and 101 eggs";
console.log("Original String: " + stock);+
    +
function minusOne(match, amount, unit) {
    amount = Number(amount) - 1;
    if ( amount == 1 ) {  // only one left, remove the 's'
	unit = unit.slice(0,unit.length-1);
    }else if ( amount == 0 ) {
	amount = "no";
    }
    return amount + " " + unit;
}

console.log(stock.replace(/(\d+) (\w+)/g,minusOne));
