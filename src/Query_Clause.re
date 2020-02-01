// https://stackoverflow.com/questions/33093807/how-to-use-gadts-across-modules-in-ocaml-without-raising-warnings
type table = pri | Table;
type from = pri | From;
type into = pri | Into;
type columns = pri | Columns;
type where = pri | Where;
type limit = pri | Limit;

type t('a) =
| Table(option(string)): t(table)
| Columns(list(string)): t(columns)
| From(option(string)): t(from)
| Into(option(string)): t(into)
| Where(list(Query_Expression.t)): t(where)
| Limit(option(int)): t(limit); 