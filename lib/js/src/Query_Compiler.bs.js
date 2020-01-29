'use strict';

var Belt_List = require("bs-platform/lib/js/belt_List.js");
var Pervasives = require("bs-platform/lib/js/pervasives.js");
var Query_Utils = require("./utils/Query_Utils.bs.js");

function compileValue(param) {
  if (typeof param === "number") {
    return "NULL";
  } else {
    switch (param.tag | 0) {
      case /* Int */0 :
          return String(param[0]);
      case /* Float */1 :
          return param[0].toString();
      case /* String */2 :
          return Query_Utils.quote(param[0]);
      case /* Bool */3 :
          return Pervasives.string_of_bool(param[0]);
      
    }
  }
}

function compileOperator(param) {
  switch (param.tag | 0) {
    case /* Eq */0 :
        return "= " + compileValue(param[0]);
    case /* NotEq */1 :
        return "<> " + compileValue(param[0]);
    case /* GreaterThan */2 :
        return "> " + compileValue(param[0]);
    case /* LessThan */3 :
        return "< " + compileValue(param[0]);
    case /* GreaterThanOrEqual */4 :
        return ">= " + compileValue(param[0]);
    case /* LessThanOrEqual */5 :
        return "<= " + compileValue(param[0]);
    case /* Between */6 :
        return "BETWEEN " + Query_Utils.joinWithAnd(/* :: */[
                    compileValue(param[0]),
                    /* :: */[
                      compileValue(param[1]),
                      /* [] */0
                    ]
                  ]);
    case /* Like */7 :
        return "LIKE " + compileValue(param[0]);
    case /* In */8 :
        return "IN :TODO";
    
  }
}

function columns(param) {
  var columns$1 = param[1];
  if (columns$1) {
    return Query_Utils.joinWithComma(Belt_List.map(columns$1, Query_Utils.quote));
  } else {
    return "*";
  }
}

function from(param) {
  var match = param[1];
  if (match !== undefined) {
    return Query_Utils.joinWithSpace(/* :: */[
                "FROM",
                /* :: */[
                  match,
                  /* [] */0
                ]
              ]);
  } else {
    return "";
  }
}

function where(param) {
  var expressions = param[1];
  if (expressions) {
    return Query_Utils.joinWithSpace(/* :: */[
                "WHERE",
                /* :: */[
                  Query_Utils.joinWithAnd(Belt_List.map(expressions, (function (param) {
                              if (param.tag) {
                                return ":TODO";
                              } else {
                                return Query_Utils.joinWithSpace(/* :: */[
                                            param[0],
                                            /* :: */[
                                              compileOperator(param[1]),
                                              /* [] */0
                                            ]
                                          ]);
                              }
                            }))),
                  /* [] */0
                ]
              ]);
  } else {
    return "";
  }
}

function limit(param) {
  var match = param[1];
  if (match !== undefined) {
    return Query_Utils.joinWithSpace(/* :: */[
                "LIMIT",
                /* :: */[
                  String(match),
                  /* [] */0
                ]
              ]);
  } else {
    return "";
  }
}

function select(statement) {
  return Query_Utils.joinWithSpace(/* :: */[
              "SELECT",
              /* :: */[
                columns(statement.columns),
                /* :: */[
                  from(statement.from),
                  /* :: */[
                    where(statement.where),
                    /* :: */[
                      limit(statement.limit),
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ]);
}

function insert(_statement) {
  return "";
}

function update(_statement) {
  return "";
}

function $$delete(_statement) {
  return "";
}

function compile(statement) {
  switch (statement.tag | 0) {
    case /* Select */0 :
        return select(statement[0]);
    case /* Insert */1 :
    case /* Update */2 :
    case /* Delete */3 :
        return "";
    
  }
}

var QU = /* alias */0;

exports.QU = QU;
exports.compileValue = compileValue;
exports.compileOperator = compileOperator;
exports.columns = columns;
exports.from = from;
exports.where = where;
exports.limit = limit;
exports.select = select;
exports.insert = insert;
exports.update = update;
exports.$$delete = $$delete;
exports.compile = compile;
/* No side effect */
