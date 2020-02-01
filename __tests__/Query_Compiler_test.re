open Jest;
module QB = Cake.Builder;

describe("Query Compiler :unit", () => {
  open Expect;
  open Query_Compiler;
  
  test("valueToString :Int", () => expect( valueToString(Int(5)) ) |> toBe("5"));
  test("valueToString :Float", () => expect( valueToString(Float(5.5)) ) |> toBe("5.5"));
  test("valueToString :String", () => expect( valueToString(String("Text")) ) |> toBe("\"Text\""));
  test("valueToString :Bool", () => expect( valueToString(Bool(true)) ) |> toBe("true"));
  test("valueToString :Null", () => expect( valueToString(Null) ) |> toBe("NULL"));

  test("operator :Eq", () => expect( Eq("col", String("yea")) -> operator ) |> toBe("col = \"yea\""));
  test("operator :NotEq", () => expect( NotEq("id", Int(55)) -> operator ) |> toBe("id <> 55"));
  test("operator :GreaterThan", () => expect( GreaterThan("currency", Float(25.8)) -> operator ) |> toBe("currency > 25.8"));
  test("operator :LessThan", () => expect( LessThan("id", Int(3)) -> operator ) |> toBe("id < 3"));
  test("operator :GreaterThanOrEqual", () => expect( GreaterThanOrEqual("id", Float(25.8)) -> operator ) |> toBe("id >= 25.8"));
  test("operator :LessThanOrEqual", () => expect( LessThanOrEqual("id", Int(3)) -> operator ) |> toBe("id <= 3"));
  test("operator :Between", () => expect( Between("age", Int(30), Int(60)) -> operator ) |> toBe("age BETWEEN 30 AND 60"));
  test("operator :Like", () => expect( Like("name", String("%wow%")) -> operator ) |> toBe("name LIKE \"%wow%\""));
  Skip.test("operator :In", () => expect( In("category", [String("No"), String("WAY")]) -> operator ) |> toBe("category IN [\"No\", \"WAY\"]"));

  test("columns :empty", () => expect( columns(Columns([])) ) |> toBe("*"));
  test("columns", () => expect( columns(Columns(["test", "column"])) ) |> toBe("\"test\", \"column\""));

  test("from :none", () => expect( from(From(None)) ) |> toBe(""));
  test("from", () => expect( from(From(Some("category"))) ) |> toBe("FROM category"));

  test("where :empty", () => expect( where(Where([])) ) |> toBe(""));
  test("where :single", () => expect( where(Where([ Single(Eq("col", Bool(true))) ])) ) |> toBe("WHERE col = true"));

  test("expression :single", () => expect( expression(Single(Eq("name", String("John")))) ) |> toBe("name = \"John\""));
  test("expression :and", () => expect( expression(And([ Single(Eq("name", String("John"))) ])) ) |> toBe("AND (name = \"John\")"));
  test("expression :or", () => expect( expression(Or([ Single(Eq("name", String("John"))) ])) ) |> toBe("OR (name = \"John\")"));
});

describe("Query Compiler :integration", () => {
  open Expect;

  test("query1", () => {

    let query = 
      QB.(Select.(
        from("category")
        -> where([Single(Eq("ali", String("veli")))])
      ))
      -> Query_Compiler.toSQL

    expect(query) |> toBe("SELECT * FROM category WHERE ali = \"veli\"");
  });

  Skip.test("query2", () => {
    let query = 
      QB.(Select.(
        from("category")
        -> where([
          Single(Eq("name", String("John"))),
          Single(Eq("surname", String("Doe"))),
        ])
      ))
      -> Query_Compiler.toSQL

    expect(query) |> toBe("SELECT * FROM category WHERE name = \"John\" AND surname = \"Doe\"");
  });
  
  test("query3", () => {
    let query = 
      QB.(Select.(
        from("category")
        -> where([
          Single(Eq("shipment_method", String("UPS"))),
          And([ Single(Eq("name", String("John"))), Or([ Single(Eq("surname", String("Doe"))) ]) ])
        ])
      ))
      -> Query_Compiler.toSQL

    expect(query) |> toBe("SELECT * FROM category WHERE shipment_method = \"UPS\" AND (name = \"John\" OR (surname = \"Doe\"))");
  });

  test("query4", () => {
    let query = 
      QB.(Select.(
        from("category")
        -> where(
          equal("shipment_method", String("UPS"))
          -> and_(equal("name", String("John")) -> or_(equal("surname", String("Doe"))))
        )
      ))
      -> Query_Compiler.toSQL

    expect(query) |> toBe("SELECT * FROM category WHERE shipment_method = \"UPS\" AND (name = \"John\" OR (surname = \"Doe\"))");
  });

  test("query5", () => {
    let query = 
      QB.(Select.(
        from("category")
        -> where(
          "shipment_method" == String("UPS")
          && ("name" == String("John") || "surname" == String("Doe"))
        )
      ))
      -> Query_Compiler.toSQL

    expect(query) |> toBe("SELECT * FROM category WHERE shipment_method = \"UPS\" AND (name = \"John\" OR (surname = \"Doe\"))");
  });
})