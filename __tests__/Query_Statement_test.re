open Jest;

describe("Query Statement: Select", () => {
  open Expect;

  test("empty", () => {
    let empty = Query_Statement.Select({ columns: `Columns([]), from: `From(None), where: `Where([]), limit: `Limit(None) });
    expect(Query_Statement.Select.empty) |> toEqual(empty) 
  });
});