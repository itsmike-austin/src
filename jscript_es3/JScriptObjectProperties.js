let txt = "";

let person = {fname: "John", lname: "Doe", age: 25};

for( let x in person ) {
    txt += person[x] + " ";
}

console.log(txt);
