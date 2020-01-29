type value = Int(int) | Float(float) | String(string) | Bool(bool) | Null;
type operator = 
| Eq(value)
| NotEq(value)
| GreaterThan(value)
| LessThan(value)
| GreaterThanOrEqual(value)
| LessThanOrEqual(value)
| Between(value, value)
| Like(value)
| In(list(value));

type compositionOperator =  And | Or | Not;
type t = Single(string, operator) | Compose(t, compositionOperator, t);