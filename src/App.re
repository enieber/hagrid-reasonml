[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <ReasonApolloHooks.ApolloProvider client=Apollo.client>
    <div className="App">
      <Header />
      <h1> {ReasonReact.string("ReFormNext demo")} </h1>
      <div style={ReactDOMRe.Style.make(~padding="100px", ())}>
        {switch (url.path) {
         | ["new-post"] => <PostAddNext />
         | ["fav-colors"] => <FavoriteColorsForm />
         | ["about"] => <About />
         | _ =>
           <p className="App-intro">
             {ReasonReact.string("Say hello to ReForm")}
           </p>
         }}
      </div>
    </div>
  </ReasonApolloHooks.ApolloProvider>;
};
