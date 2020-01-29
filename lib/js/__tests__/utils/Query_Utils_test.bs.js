'use strict';

var Jest = require("@glennsl/bs-jest/lib/js/src/jest.js");
var Query_Utils = require("../../src/utils/Query_Utils.bs.js");

Jest.describe("Query Utils", (function (param) {
        Jest.test("joinWithSpace", (function (param) {
                var e = Query_Utils.joinWithSpace(/* :: */[
                      "column",
                      /* :: */[
                        "value",
                        /* [] */0
                      ]
                    ]);
                return Jest.Expect.toEqual("column value", Jest.Expect.expect(e));
              }));
        Jest.test("joinWithAnd", (function (param) {
                var e = Query_Utils.joinWithAnd(/* :: */[
                      "column",
                      /* :: */[
                        "value",
                        /* [] */0
                      ]
                    ]);
                return Jest.Expect.toEqual("column AND value", Jest.Expect.expect(e));
              }));
        Jest.test("joinWithOr", (function (param) {
                var e = Query_Utils.joinWithOr(/* :: */[
                      "column",
                      /* :: */[
                        "value",
                        /* [] */0
                      ]
                    ]);
                return Jest.Expect.toEqual("column OR value", Jest.Expect.expect(e));
              }));
        Jest.test("joinWithComma", (function (param) {
                var e = Query_Utils.joinWithComma(/* :: */[
                      "column",
                      /* :: */[
                        "value",
                        /* [] */0
                      ]
                    ]);
                return Jest.Expect.toEqual("column, value", Jest.Expect.expect(e));
              }));
        return Jest.test("quote", (function (param) {
                      var e = Query_Utils.quote("column");
                      return Jest.Expect.toEqual("\"column\"", Jest.Expect.expect(e));
                    }));
      }));

/*  Not a pure module */
