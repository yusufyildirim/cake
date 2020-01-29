'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Query_Statement = require("./Query_Statement.bs.js");

var select = Query_Statement.Select.empty;

function from(t, table) {
  if (t.tag) {
    return t;
  } else {
    var r = t[0];
    return /* Select */Block.__(0, [{
                columns: r.columns,
                from: /* `From */[
                  781963658,
                  table
                ],
                where: r.where,
                limit: r.limit
              }]);
  }
}

function columns(t, columns$1) {
  if (t.tag) {
    return t;
  } else {
    var r = t[0];
    return /* Select */Block.__(0, [{
                columns: /* `Columns */[
                  -1062546243,
                  columns$1
                ],
                from: r.from,
                where: r.where,
                limit: r.limit
              }]);
  }
}

function where(t, column, operator) {
  switch (t.tag | 0) {
    case /* Select */0 :
        var r = t[0];
        var match = r.where;
        return /* Select */Block.__(0, [{
                    columns: r.columns,
                    from: r.from,
                    where: /* `Where */[
                      -588795961,
                      /* :: */[
                        /* Single */Block.__(0, [
                            column,
                            operator
                          ]),
                        match[1]
                      ]
                    ],
                    limit: r.limit
                  }]);
    case /* Insert */1 :
        return t;
    case /* Update */2 :
        var r$1 = t[0];
        var match$1 = r$1.where;
        return /* Update */Block.__(2, [{
                    table: r$1.table,
                    where: /* `Where */[
                      -588795961,
                      /* :: */[
                        /* Single */Block.__(0, [
                            column,
                            operator
                          ]),
                        match$1[1]
                      ]
                    ]
                  }]);
    case /* Delete */3 :
        var r$2 = t[0];
        var match$2 = r$2.where;
        return /* Delete */Block.__(3, [{
                    table: r$2.table,
                    where: /* `Where */[
                      -588795961,
                      /* :: */[
                        /* Single */Block.__(0, [
                            column,
                            operator
                          ]),
                        match$2[1]
                      ]
                    ]
                  }]);
    
  }
}

function limit(t, number) {
  if (t.tag) {
    return t;
  } else {
    var r = t[0];
    return /* Select */Block.__(0, [{
                columns: r.columns,
                from: r.from,
                where: r.where,
                limit: /* `Limit */[
                  137269019,
                  number
                ]
              }]);
  }
}

exports.select = select;
exports.from = from;
exports.columns = columns;
exports.where = where;
exports.limit = limit;
/* No side effect */
