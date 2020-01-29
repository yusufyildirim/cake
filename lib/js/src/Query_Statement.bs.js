'use strict';

var Block = require("bs-platform/lib/js/block.js");

var statement = {
  columns: /* `Columns */[
    -1062546243,
    /* [] */0
  ],
  from: /* `From */[
    781963658,
    undefined
  ],
  where: /* `Where */[
    -588795961,
    /* [] */0
  ],
  limit: /* `Limit */[
    137269019,
    undefined
  ]
};

var empty = /* Select */Block.__(0, [statement]);

var Select = {
  statement: statement,
  empty: empty
};

var statement$1 = {
  table: ""
};

var empty$1 = /* Insert */Block.__(1, [statement$1]);

var Insert = {
  statement: statement$1,
  empty: empty$1
};

var statement$2 = {
  table: "",
  where: /* `Where */[
    -588795961,
    /* [] */0
  ]
};

var empty$2 = /* Update */Block.__(2, [statement$2]);

var Update = {
  statement: statement$2,
  empty: empty$2
};

var statement$3 = {
  table: "",
  where: /* `Where */[
    -588795961,
    /* [] */0
  ]
};

var empty$3 = /* Delete */Block.__(3, [statement$3]);

var Delete = {
  statement: statement$3,
  empty: empty$3
};

exports.Select = Select;
exports.Insert = Insert;
exports.Update = Update;
exports.Delete = Delete;
/* No side effect */
