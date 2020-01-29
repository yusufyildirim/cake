open Jest;

describe("Query Utils", () => {
  open Expect;

  test("joinWithSpace", () => {
    let e = Query_Utils.joinWithSpace(["column", "value"])
    expect(e) |> toEqual("column value");
  });

  test("joinWithAnd", () => {
    let e = Query_Utils.joinWithAnd(["column", "value"])
    expect(e) |> toEqual("column AND value");
  });

  test("joinWithOr", () => {
    let e = Query_Utils.joinWithOr(["column", "value"])
    expect(e) |> toEqual("column OR value");
  });

  test("joinWithComma", () => {
    let e = Query_Utils.joinWithComma(["column", "value"])
    expect(e) |> toEqual("column, value");
  });

  test("quote", () => {
    let e = Query_Utils.quote("column")
    expect(e) |> toEqual("\"column\"");
  });
});