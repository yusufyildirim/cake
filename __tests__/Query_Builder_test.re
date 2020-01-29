open Jest;
open Query_Statement;
open Query_Builder;
open Query_Expression;

let selectStatement = Query_Statement.Select.statement;
let select = Query_Statement.Select.empty;
let insertStatement = Query_Statement.Insert.statement;
let insert = Query_Statement.Insert.empty;
let updateStatement = Query_Statement.Update.statement;
let update = Query_Statement.Update.empty;
let deleteStatement = Query_Statement.Delete.statement;
let delete = Query_Statement.Delete.empty;


describe("QB constructors", () => {
  open Expect;

  test("select", () => expect(select) |> toEqual(Query_Statement.Select.empty));
});

describe("from", () => {
  open Expect;
  let table = "tableName";

  test("from :select", () => expect(select -> from(table)) |> toEqual(Select({...selectStatement, from: `From(Some(table))})))
  test("from :update", () => expect(update -> from(table)) |> toEqual(update))
  test("from :delete", () => expect(delete -> from(table)) |> toEqual(delete))
  test("from :insert", () => expect(insert -> from(table)) |> toEqual(insert))
});

describe("columns", () => {
  open Expect;
  let cols = ["col1", "col2"];

  test("columns :select", () => expect(select -> columns(cols)) |> toEqual(Select({...selectStatement, columns: `Columns(cols)})))
  test("columns :update", () => expect(update -> columns(cols)) |> toEqual(update))
  test("columns :delete", () => expect(delete -> columns(cols)) |> toEqual(delete))
  test("columns :insert", () => expect(insert -> columns(cols)) |> toEqual(insert))
});

describe("where", () => {
  open Expect;

  let col = "col";
  let op = Eq(String("value"));
  let whereClause = `Where([ Single(col, op)])
  let whereClause2 = `Where([ Single(col, op), Single(col, op)])

  test("where :select", () => expect(select -> where(col, op)) |> toEqual(Select({ ...selectStatement, where: whereClause })))
  test("where :update", () => expect(update -> where(col, op)) |> toEqual(Update({ ...updateStatement, where: whereClause })))
  test("where :delete", () => expect(delete -> where(col, op)) |> toEqual(Delete({ ...deleteStatement, where: whereClause })))
  test("insert :insert", () => expect(insert -> where(col, op)) |> toEqual(insert))

  test("where multiple :select", () => expect(select -> where(col, op) -> where(col, op)) |> toEqual(Select({ ...selectStatement, where: whereClause2 })))
  test("where multiple :update", () => expect(update -> where(col, op) -> where(col, op)) |> toEqual(Update({ ...updateStatement, where: whereClause2 })))
  test("where multiple :delete", () => expect(delete -> where(col, op) -> where(col, op)) |> toEqual(Delete({ ...deleteStatement, where: whereClause2 })))
  test("insert multiple :insert", () => expect(insert -> where(col, op) -> where(col, op)) |> toEqual(insert))
});

describe("limit", () => {
  open Expect;
  let number = 99;

  test("limit :select", () => expect(select -> limit(number)) |> toEqual(Select({...selectStatement, limit: `Limit(Some(number))})))
  test("limit :update", () => expect(update -> limit(number)) |> toEqual(update))
  test("limit :delete", () => expect(delete -> limit(number)) |> toEqual(delete))
  test("limit :insert", () => expect(insert -> limit(number)) |> toEqual(insert))
})