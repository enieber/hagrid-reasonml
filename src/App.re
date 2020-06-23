[@react.component]
let make = () => {
  let url = ReasonReactRouter.useUrl();

  <ReasonApollo.Provider client=Apollo.client>
    <div className="App">
      <Header />
      <div style={ReactDOMRe.Style.make(~padding="100px", ())}>
        {switch (url.path) {
         | ["sobre"] => <About />
         | ["items"] => <Items />
         | ["cofres"] => <Safes />
         | ["salas"] => <Room />
         | ["predios"] => <Company />
         | _ => <Home />
         }}
      </div>
    </div>
  </ReasonApollo.Provider>;
};
