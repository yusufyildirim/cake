'use strict';

var Jest = require("@glennsl/bs-jest/lib/js/src/jest.js");
var Block = require("bs-platform/lib/js/block.js");
var Query_Builder = require("../src/Query_Builder.bs.js");
var Query_Statement = require("../src/Query_Statement.bs.js");

var selectStatement = Query_Statement.Select.statement;

var select = Query_Statement.Select.empty;

var insertStatement = Query_Statement.Insert.statement;

var insert = Query_Statement.Insert.empty;

var updateStatement = Query_Statement.Update.statement;

var update = Query_Statement.Update.empty;

var deleteStatement = Query_Statement.Delete.statement;

var $$delete = Query_Statement.Delete.empty;

Jest.describe("QB constructors", (function (param) {
        return Jest.test("select", (function (param) {
                      return Jest.Expect.toEqual(Query_Statement.Select.empty, Jest.Expect.expect(select));
                    }));
      }));

Jest.describe("from", (function (param) {
        var table = "tableName";
        Jest.test("from :select", (function (param) {
                return Jest.Expect.toEqual(/* Select */Block.__(0, [{
                                columns: selectStatement.columns,
                                from: /* `From */[
                                  781963658,
                                  table
                                ],
                                where: selectStatement.where,
                                limit: selectStatement.limit
                              }]), Jest.Expect.expect(Query_Builder.from(select, table)));
              }));
        Jest.test("from :update", (function (param) {
                return Jest.Expect.toEqual(update, Jest.Expect.expect(Query_Builder.from(update, table)));
              }));
        Jest.test("from :delete", (function (param) {
                return Jest.Expect.toEqual($$delete, Jest.Expect.expect(Query_Builder.from($$delete, table)));
              }));
        return Jest.test("from :insert", (function (param) {
                      return Jest.Expect.toEqual(insert, Jest.Expect.expect(Query_Builder.from(insert, table)));
                    }));
      }));

Jest.describe("columns", (function (param) {
        var cols = /* :: */[
          "col1",
          /* :: */[
            "col2",
            /* [] */0
          ]
        ];
        Jest.test("columns :select", (function (param) {
                return Jest.Expect.toEqual(/* Select */Block.__(0, [{
                                columns: /* `Columns */[
                                  -1062546243,
                                  cols
                                ],
                                from: selectStatement.from,
                                where: selectStatement.where,
                                limit: selectStatement.limit
                              }]), Jest.Expect.expect(Query_Builder.columns(select, cols)));
              }));
        Jest.test("columns :update", (function (param) {
                return Jest.Expect.toEqual(update, Jest.Expect.expect(Query_Builder.columns(update, cols)));
              }));
        Jest.test("columns :delete", (function (param) {
                return Jest.Expect.toEqual($$delete, Jest.Expect.expect(Query_Builder.columns($$delete, cols)));
              }));
        return Jest.test("columns :insert", (function (param) {
                      return Jest.Expect.toEqual(insert, Jest.Expect.expect(Query_Builder.columns(insert, cols)));
                    }));
      }));

Jest.describe("where", (function (param) {
        var col = "col";
        var op = /* Eq */Block.__(0, [/* String */Block.__(2, ["value"])]);
        var whereClause_001 = /* :: */[
          /* Single */Block.__(0, [
              col,
              op
            ]),
          /* [] */0
        ];
        var whereClause = /* `Where */[
          -588795961,
          whereClause_001
        ];
        var whereClause2_001 = /* :: */[
          /* Single */Block.__(0, [
              col,
              op
            ]),
          /* :: */[
            /* Single */Block.__(0, [
                col,
                op
              ]),
            /* [] */0
          ]
        ];
        var whereClause2 = /* `Where */[
          -588795961,
          whereClause2_001
        ];
        Jest.test("where :select", (function (param) {
                return Jest.Expect.toEqual(/* Select */Block.__(0, [{
                                columns: selectStatement.columns,
                                from: selectStatement.from,
                                where: whereClause,
                                limit: selectStatement.limit
                              }]), Jest.Expect.expect(Query_Builder.where(select, col, op)));
              }));
        Jest.test("where :update", (function (param) {
                return Jest.Expect.toEqual(/* Update */Block.__(2, [{
                                table: updateStatement.table,
                                where: whereClause
                              }]), Jest.Expect.expect(Query_Builder.where(update, col, op)));
              }));
        Jest.test("where :delete", (function (param) {
                return Jest.Expect.toEqual(/* Delete */Block.__(3, [{
                                table: deleteStatement.table,
                                where: whereClause
                              }]), Jest.Expect.expect(Query_Builder.where($$delete, col, op)));
              }));
        Jest.test("insert :insert", (function (param) {
                return Jest.Expect.toEqual(insert, Jest.Expect.expect(Query_Builder.where(insert, col, op)));
              }));
        Jest.test("where multiple :select", (function (param) {
                return Jest.Expect.toEqual(/* Select */Block.__(0, [{
                                columns: selectStatement.columns,
                                from: selectStatement.from,
                                where: whereClause2,
                                limit: selectStatement.limit
                              }]), Jest.Expect.expect(Query_Builder.where(Query_Builder.where(select, col, op), col, op)));
              }));
        Jest.test("where multiple :update", (function (param) {
                return Jest.Expect.toEqual(/* Update */Block.__(2, [{
                                table: updateStatement.table,
                                where: whereClause2
                              }]), Jest.Expect.expect(Query_Builder.where(Query_Builder.where(update, col, op), col, op)));
              }));
        Jest.test("where multiple :delete", (function (param) {
                return Jest.Expect.toEqual(/* Delete */Block.__(3, [{
                                table: deleteStatement.table,
                                where: whereClause2
                              }]), Jest.Expect.expect(Query_Builder.where(Query_Builder.where($$delete, col, op), col, op)));
              }));
        return Jest.test("insert multiple :insert", (function (param) {
                      return Jest.Expect.toEqual(insert, Jest.Expect.expect(Query_Builder.where(Query_Builder.where(insert, col, op), col, op)));
                    }));
      }));

Jest.describe("limit", (function (param) {
        Jest.test("limit :select", (function (param) {
                return Jest.Expect.toEqual(/* Select */Block.__(0, [{
                                columns: selectStatement.columns,
                                from: selectStatement.from,
                                where: selectStatement.where,
                                limit: /* `Limit */[
                                  137269019,
                                  99
                                ]
                              }]), Jest.Expect.expect(Query_Builder.limit(select, 99)));
              }));
        Jest.test("limit :update", (function (param) {
                return Jest.Expect.toEqual(update, Jest.Expect.expect(Query_Builder.limit(update, 99)));
              }));
        Jest.test("limit :delete", (function (param) {
                return Jest.Expect.toEqual($$delete, Jest.Expect.expect(Query_Builder.limit($$delete, 99)));
              }));
        return Jest.test("limit :insert", (function (param) {
                      return Jest.Expect.toEqual(insert, Jest.Expect.expect(Query_Builder.limit(insert, 99)));
                    }));
      }));

exports.selectStatement = selectStatement;
exports.select = select;
exports.insertStatement = insertStatement;
exports.insert = insert;
exports.updateStatement = updateStatement;
exports.update = update;
exports.deleteStatement = deleteStatement;
exports.$$delete = $$delete;
/*  Not a pure module */
