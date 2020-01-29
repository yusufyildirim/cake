'use strict';

var Jest = require("@glennsl/bs-jest/lib/js/src/jest.js");

Jest.describe("Query Builder", (function (param) {
        return Jest.test("1 eq 1", (function (param) {
                      return Jest.Expect.toEqual(1, Jest.Expect.expect(1));
                    }));
      }));

/*  Not a pure module */
