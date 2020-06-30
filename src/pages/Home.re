type hagrid_items = {
  description: string
}

type result =  {
  .
  "data": option(array({ . description: string, id: string }))
 };

module GetDashboard = [%graphql
{|
  query getDashboard {
    hagrid_items {
      id
      description
    }
  }
|}
];

module Query = ReasonApollo.CreateQuery(GetDashboard);

[@react.component]
let make = () => {
  <Query>
      ...{({result}) =>
        switch (result) {
        | Loading => <div>{"Carregando"->ReasonReact.string}</div>
        | Error(error) => <div>{"Deu ruim"->ReasonReact.string}</div>
        | Data(resonse) => <div>{resonse##hagrid_items->Belt.Array.forEach(item => (
          <li key={item##id->ReasonReact.string}>item##description->ReasonReact.string</li>) )}</div>
        }
      }
    </Query>
  ;
};