'use strict';

var $$String = require("bs-platform/lib/js/string.js");

function joinWithSpace(list) {
  return $$String.concat(" ", list);
}

function joinWithAnd(list) {
  return $$String.concat(" AND ", list);
}

function joinWithOr(list) {
  return $$String.concat(" OR ", list);
}

function joinWithComma(list) {
  return $$String.concat(", ", list);
}

function quote(s) {
  return "\"" + (s + "\"");
}

exports.joinWithSpace = joinWithSpace;
exports.joinWithAnd = joinWithAnd;
exports.joinWithOr = joinWithOr;
exports.joinWithComma = joinWithComma;
exports.quote = quote;
/* No side effect */
