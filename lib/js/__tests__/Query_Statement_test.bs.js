'use strict';

var Jest = require("@glennsl/bs-jest/lib/js/src/jest.js");
var Block = require("bs-platform/lib/js/block.js");
var Query_Statement = require("../src/Query_Statement.bs.js");

Jest.describe("Query Statement: Select", (function (param) {
        return Jest.test("empty", (function (param) {
                      return Jest.Expect.toEqual(/* Select */Block.__(0, [{
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
                                    }]), Jest.Expect.expect(Query_Statement.Select.empty));
                    }));
      }));

/*  Not a pure module */
