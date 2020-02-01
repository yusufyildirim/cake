open Query_Expression;

let equal = (col, value) => [Single(Eq(col, value))];
let notEqual = (col, value) => [Single(NotEq(col, value))];
let greaterThan = (col, value) => [Single(GreaterThan(col, value))];
let lessThan = (col, value) => [Single(LessThan(col, value))];
let greaterThanOrEqual = (col, value) => [Single(GreaterThanOrEqual(col, value))];
let lessThanOrEqual = (col, value) => [Single(LessThanOrEqual(col, value))];
let between = (col, value1, value2) => [Single(Between(col, value1, value2))];
let like = (col, value) => [Single(Like(col, value))];
let in_ = (col, list) => [Single(In(col, list))];

let and_ = (l1, l2) => List.concat(l1, [And(l2)]);
let or_ = (l1, l2) => List.concat(l1, [Or(l2)]);

let (==) = equal;
let (!=) = notEqual;
let (&&) = and_;
let (||) = or_;

/*
  where("id", Eq(Int(5)))
  -> where(eq("id", Int(5)))
  -> where(eq("id", Int(5)) -> and_(eq("id", "")))
  -> where(
    eq("name", String("Shirts"))
    -> and(
      in("name", [ String("Sweatshirts"), String("Hoodies") ])
      -> or(
        eq("mehmet", String("ali"))
      )
    )
  );

  // With infix operators
  where(
    "name" == String("Shirts")
    && ( "name" -> in_([ String("Sweatshirts"), String("Hoodies") ]) || "mehmet" == String("ali"))
    )

  // Obj Represantation
  [
    Single("ali", Eq( "veli")),
    And([
      Single("ali", Eq( "veli")),
      Single("ali", Eq( "veli"))
    ])
  ]
*/