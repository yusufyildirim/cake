open Jest;
module QB = Cake.Builder;
module QC = Cake.Compiler;

describe("Query Compiler :unit", () => {
  open Expect;
  open Query_Compiler;
  
  test("valueToString :Int", () => expect( valueToString(Int(5)) ) |> toBe("5"));
  test("valueToString :Float", () => expect( valueToString(Float(5.5)) ) |> toBe("5.5"));
  test("valueToString :String", () => expect( valueToString(String("Text")) ) |> toBe("\"Text\""));
  test("valueToString :Bool", () => expect( valueToString(Bool(true)) ) |> toBe("true"));
  test("valueToString :Null", () => expect( valueToString(Null) ) |> toBe("NULL"));

  test("orderDirectionToString: Asc", () => expect( orderDirectionToString(Asc) ) |> toBe("ASC"));
  test("orderDirectionToString: Desc", () => expect( orderDirectionToString(Desc) ) |> toBe("DESC"));

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
  test("columns", () => expect( columns(Columns(["test", "column"])) ) |> toBe("test, column"));

  test("from :none", () => expect( from(From(None)) ) |> toBe(""));
  test("from", () => expect( from(From(Some("category"))) ) |> toBe("FROM category"));

  test("where :empty", () => expect( where(Where([])) ) |> toBe(""));
  test("where :single", () => expect( where(Where([ Single(Eq("col", Bool(true))) ])) ) |> toBe("WHERE col = true"));

  test("limit :none", () => expect( limit(Limit(None)) ) |> toBe(""));
  test("limit", () => expect( limit(Limit(Some(99))) ) |> toBe("LIMIT 99"));

  test("expression :single", () => expect( expression(Single(Eq("name", String("John")))) ) |> toBe("name = \"John\""));
  test("expression :and", () => expect( expression(And([ Single(Eq("name", String("John"))) ])) ) |> toBe("AND (name = \"John\")"));
  test("expression :or", () => expect( expression(Or([ Single(Eq("name", String("John"))) ])) ) |> toBe("OR (name = \"John\")"));

  test("groupBy: empty", () => expect( groupBy(GroupBy([])) ) |> toBe(""));
  test("groupBy :single", () => expect( groupBy(GroupBy(["category"]))) |> toBe("GROUP BY category"));
  test("groupBy", () => expect(groupBy(GroupBy(["category", "name"]))) |> toBe("GROUP BY category, name"));

  test("orderBy: empty", () => expect( orderBy(OrderBy([])) ) |> toBe(""));
  test("orderBy", () => expect( orderBy(OrderBy([ ("col", Asc), ("otherCol", Desc) ])) ) |> toBe("ORDER BY col ASC, otherCol DESC"));

  // INSERT
  test("into :empty", () => expect( into(Into(None)) ) |> toBe(""));
  test("into", () => expect( into(Into(Some("table"))) ) |> toBe("INTO table"));

  test("values :empty", () => expect( values(Values([])) ) |> toBe(""));
  test("values", () => expect( values(Values([ [String("John"), Int(24)] ])) ) |> toBe("VALUES (\"John\", 24)"));
});


describe("Query Compiler :integration", () => {
  open Expect;

  test("select :from", () => {
    open QB;
    expect(Select.from("users") -> QC.toSQL)|> toBe("SELECT * FROM users");
  });

  test("select :columns", () => {
    open QB;
    expect(Select.(from("users") -> columns(["name", "surname"])) -> QC.toSQL)|> toBe("SELECT name, surname FROM users");
  });

  test("select :where", () => {
    open QB;
    expect(Select.(from("users") -> where("name" == String("Adam"))) -> QC.toSQL)|> toBe("SELECT * FROM users WHERE name = \"Adam\"");
  });

  test("select :limit", () => {
    open QB;
    expect(Select.(from("users") -> limit(99)) -> QC.toSQL)|> toBe("SELECT * FROM users LIMIT 99");
  });

  test("select :groupBy", () => {
    open QB;
    expect(Select.(from("users") -> groupBy(["name"])) -> QC.toSQL)|> toBe("SELECT * FROM users GROUP BY name");
  });

  test("select :orderBy", () => {
    open QB;
    expect(Select.(from("users") -> orderBy([("name", Asc)])) -> QC.toSQL)|> toBe("SELECT * FROM users ORDER BY name ASC");
  });

  test("query1", () => {

    let query = {
      open QB;
      Select.( from("category") -> where([Single(Eq("ali", String("veli")))]) )
      -> Query_Compiler.toSQL
    }

    expect(query) |> toBe("SELECT * FROM category WHERE ali = \"veli\"");
  });

  Skip.test("query2", () => {
    let query = {
      open QB;
      Select.(
        from("category")
        -> where([
          Single(Eq("name", String("John"))),
          Single(Eq("surname", String("Doe"))),
        ])
      ) -> Query_Compiler.toSQL
    }

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
          -> and_(
            equal("name", String("John"))
            -> or_(equal("surname", String("Doe")))
          )
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
  
  test("INSERT", () => {
    open QB;
    let query = 
      Insert.(
        into("user")
        -> columns(["name", "age"])
        -> values([
          [String("Yusuf"), Int(18)],
        ])
      )
      -> Query_Compiler.toSQL

    expect(query) |> toBe("INSERT INTO user (name, age) VALUES (\"Yusuf\", 18)");
  });

  test("INSERT 2", () => {
    open QB;
    let query = 
      Insert.(
        into("user")
        -> columns(["name", "age"])
        -> values([
          [String("Yusuf"), Int(24)],
          [String("John"), Int(43)],
        ])
      )
      -> Query_Compiler.toSQL

    expect(query) |> toBe("INSERT INTO user (name, age) VALUES (\"Yusuf\", 24), (\"John\", 43)");
  });
})