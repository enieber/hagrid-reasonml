open ApolloInMemoryCache;

type dataObject = {
  .
  "__typename": string,
  "id": string,
  "key": string,
};

/* Create an InMemoryCache */
let inMemoryCache =
  createInMemoryCache(~dataIdFromObject=(obj: dataObject) => obj##id, ());

/* Create an HTTP Link */
let httpLink =
  ApolloLinks.createHttpLink(
    ~uri="http://hagrid-startse.herokuapp.com/v1/graphql",
    (),
  );

let client =
  ReasonApollo.createApolloClient(
    ~cache=inMemoryCache /* restore method can be piped e.g. inMemoryCache |> restore(window.__APOLLO__) */,
    ~link=httpLink,
    (),
  );
