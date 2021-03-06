// https://stackoverflow.com/questions/33093807/how-to-use-gadts-across-modules-in-ocaml-without-raising-warnings
type table = pri | Table;
type from = pri | From;
type into = pri | Into;
type columns = pri | Columns;
type where = pri | Where;
type limit = pri | Limit;
type groupBy = pri | GroupBy;
type orderBy = pri | OrderBy;
type values = pri | Values;

type orderDirection = Asc | Desc;
type orderRule = (string, orderDirection);

type t('a) =
| Table(option(string)): t(table)
| Columns(list(string)): t(columns)
| From(option(string)): t(from)
| Into(option(string)): t(into)
| Where(list(Query_Expression.t)): t(where)
| Limit(option(int)): t(limit)
| GroupBy(list(string)): t(groupBy)
| OrderBy(list(orderRule)): t(orderBy)
| Values(list(list(Query_Expression.value))): t(values);