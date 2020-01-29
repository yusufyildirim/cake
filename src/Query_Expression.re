type value = Int(int) | String(string) | Bool(bool);
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