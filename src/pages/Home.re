module GetDashboard = [%graphql
{|
  query getDashboard {
    hagrid_items {
      id
    }
  }
|}
];

module Query = ReasonApollo.CreateQuery(GetDashboard);

[@react.component]
let make = () => {
  <div>
    <Query>
      ...{({result}) =>
        switch (result) {
        | Loading => <div>{"Carregando"->ReasonReact.string}</div>
        | Error(error) => <div>{"Deu ruim"->ReasonReact.string}</div>
        | Data(response) =>
          <div>         
            response.hagrid_items
            ->Belt.Array.map((item) => <li key={item.id}>{item.id->React.string}</li>)
          </div>
        }
      }
    </Query>
    <p>"Home page"->ReasonReact.string</p>
  </div>  
  ;
};