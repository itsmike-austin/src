function stripComments(code) {
    return code.replace(/\/\.*[^]*?\*\//g,"");
}

console.log("Strip comments from javascript code");
console.log("stripping from \"1 /* a */+/* b */ 1\"");
console.log(stripComments("1 /* a */+/* b */ 1"));
