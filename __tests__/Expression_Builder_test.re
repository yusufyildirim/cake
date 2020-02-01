open Jest;
open Expression_Builder;
open Query_Expression;

describe("Expression Builder", () => {
  open Expect;
  test("equal", () => expect( equal("col", String("value")) ) |> toEqual([ Single(Eq("col", String("value"))) ]));
  test("notEqual", () => expect( notEqual("name", String("John")) ) |> toEqual([ Single(NotEq("name", String("John"))) ]));
  test("greaterThan", () => expect( greaterThan("age", Int(50)) ) |> toEqual([ Single(GreaterThan("age", Int(50))) ]));
  test("lessThan", () => expect( lessThan("age", Int(30)) ) |> toEqual([ Single(LessThan("age", Int(30))) ]));
  test("greaterThanOrEqual", () => expect( greaterThanOrEqual("height", Int(22)) ) |> toEqual([ Single(GreaterThanOrEqual("height", Int(22))) ]));
  test("lessThanOrEqual", () => expect( lessThanOrEqual("age", Int(18)) ) |> toEqual([ Single(LessThanOrEqual("age", Int(18))) ]));
  test("between", () => expect( between("age", Int(18), Int(25)) ) |> toEqual([ Single(Between("age", Int(18), Int(25))) ]));
  test("like", () => expect( like("name", String("%John%")) ) |> toEqual([ Single(Like("name", String("%John%"))) ]));
  test("in_", () => expect( in_("age", [Int(18), Int(25)]) ) |> toEqual([ Single(In("age", [Int(18), Int(25)])) ]));
  test("and_", () => 
    expect( and_([ Single(Eq("age", Int(20))) ], [ Single(Eq("name", String("John"))), Single(Eq("surname", String("Doe"))) ]) )
    |> toEqual([ Single(Eq("age", Int(20))), And([ Single(Eq("name", String("John"))), Single(Eq("surname", String("Doe"))) ]) ])
  );
  test("or_", () => 
    expect( or_([ Single(Eq("age", Int(20))) ], [ Single(Eq("name", String("John"))), Single(Eq("surname", String("Doe"))) ]) )
    |> toEqual([ Single(Eq("age", Int(20))), Or([ Single(Eq("name", String("John"))), Single(Eq("surname", String("Doe"))) ]) ])
  );
});