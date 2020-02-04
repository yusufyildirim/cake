open Jest;
open Cake.Builder;
open Query_Statement;
open Query_Expression;
open Query_Clause;

let table = "category"
let col = "col";
let eqExpr = Single(Eq(col, String("value")));
let cols = ["col1", "col2"];
let number = 88;
let whereClause = Where([ eqExpr ])
let whereClause2 = Where([ eqExpr, eqExpr ]);

describe("Select", () => {
  open Expect;
  open Select;

  test("from", () => expect( from(table) ) |> toEqual( Select({ ...statement, from: From(Some(table)) }) ));
  test("where", () => expect( empty -> where([ eqExpr ]) ) |> toEqual( Select({ ...statement, where: whereClause }) ));
  test("where multi", () => expect( empty -> where([ eqExpr ]) -> where([ eqExpr ]) ) |> toEqual( Select({ ...statement, where: whereClause2 }) ));
  test("columns", () => expect( empty -> columns(cols) ) |> toEqual( Select({...statement, columns: Columns(cols)}) ));
  test("limit", () => expect( empty -> limit(number) ) |> toEqual( Select({...statement, limit: Limit(Some(number))}) ));
  test("orderBy", () => expect( empty -> orderBy([("id", Asc)]) ) |> toEqual( Select({...statement, orderBy: OrderBy([("id", Asc)])}) ));
  test("groupBy", () => expect( empty -> groupBy(["category"]) ) |> toEqual( Select({...statement, groupBy: GroupBy(["category"])}) ));
});

describe("Insert", () => {
  open Expect;
  open Insert;

  test("into", () => expect( into(table) ) |> toEqual( Insert({ into: Into(Some(table)) }) ));
});

describe("Update", () => {
  open Expect;
  open Update;

  test("where", () => expect( empty -> where([ eqExpr ]) ) |> toEqual( Update({...statement, where: whereClause}) ));
  test("where multi", () => expect( empty -> where([ eqExpr ]) -> where([ eqExpr ]) ) |> toEqual( Update({ ...statement, where: whereClause2 }) ));
});

describe("Delete", () => {
  open Expect;
  open Delete;

  test("where", () => expect( empty -> where([ eqExpr ]) ) |> toEqual( Delete({...statement, where: whereClause}) ));
  test("where multi", () => expect( empty -> where([ eqExpr ]) -> where([ eqExpr ]) ) |> toEqual( Delete({ ...statement, where: whereClause2 }) ));
});