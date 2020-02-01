type value = Int(int) | Float(float) | String(string) | Bool(bool) | Null;
type operator = 
| Eq(string, value)
| NotEq(string, value)
| GreaterThan(string, value)
| LessThan(string, value)
| GreaterThanOrEqual(string, value)
| LessThanOrEqual(string, value)
| Between(string, value, value)
| Like(string, value)
| In(string, list(value));

type t = Single(operator) | And(list(t)) | Or(list(t));