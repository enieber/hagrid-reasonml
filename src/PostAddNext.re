open BsReform;
module StateLenses = [%lenses
  type state = {
    description: string,
    title: string,
    acceptTerms: bool,
  }
];
module PostAddForm = ReForm.Make(StateLenses);

module PostAddMutationConfig = [%graphql
  {|
  mutation PostAddMutation ($description: String!, $title: String!) {
    createPost(description: $description, title: $title) {
      id
      title
      description
    }
  }
|}
];

module PostAddMutation =
  ReasonApolloHooks.Mutation.Make(PostAddMutationConfig);

module FieldString = {
  [@react.component]
  let make = (~field, ~label) => {
    <PostAddForm.Field
      field
      render={({handleChange, error, value, validate}) => {
        /* Open up your browser DevTools to see how the changes are only applied when you change the respective component */
        Js.log(label);
        <label>
          <span> {React.string(label)} </span>
          <input
            value
            onChange={Helpers.handleChange(handleChange)}
            onBlur={_ => validate()}
          />
          <p> {error->Belt.Option.getWithDefault("")->React.string} </p>
        </label>;
      }}
    />;
  };
};

[@react.component]
let make = () => {
  let (mutate, result, _) = PostAddMutation.use(~client=Apollo.client, ());

  let reform =
    PostAddForm.use(
      ~validationStrategy=OnDemand,
      ~schema={
        PostAddForm.Validation.Schema([|
          Custom(
            Title,
            values =>
              Js.String.length(values.title) > 20
                ? Error("Keep it short!") : Valid,
          ),
          StringNonEmpty(Description),
          Custom(
            AcceptTerms,
            values =>
              values.acceptTerms == false
                ? Error("You must accept all the terms") : Valid,
          ),
        |]);
      },
      ~onSubmit=
        ({state}) => {
          mutate(
            ~variables=
              PostAddMutationConfig.make(
                ~title=state.values.title,
                ~description=state.values.description,
                (),
              )##variables,
            (),
          )
          |> ignore;

          None;
        },
      ~initialState={title: "", description: "", acceptTerms: false},
      (),
    );

  <PostAddForm.Provider value=reform>
    {switch (result) {
     | Error(_error) => <p> {React.string("Something went wrong...")} </p>
     | Data(data) =>
       <div>
         <h2>
           {data##createPost
            ->Belt.Option.map(post =>
                "Post#" ++ post##id ++ " " ++ post##title
              )
            ->Belt.Option.getWithDefault("")
            ->React.string}
         </h2>
         <p>
           {data##createPost
            ->Belt.Option.map(post => post##description)
            ->Belt.Option.getWithDefault("")
            ->React.string}
         </p>
       </div>
     | _ =>
       <form
         onSubmit={event => {
           ReactEvent.Synthetic.preventDefault(event);
           reform.submit();
         }}>
         <FieldString field=StateLenses.Title label="Title" />
         <FieldString field=StateLenses.Description label="Description" />
         <PostAddForm.Field
           field=StateLenses.AcceptTerms
           render={({handleChange, error, value}) =>
             <label>
               <p>
                 <span> {"Accept terms? " |> React.string} </span>
                 <input
                   type_="checkbox"
                   value={string_of_bool(value)}
                   onChange={event =>
                     ReactEvent.Form.target(event)##checked |> handleChange
                   }
                 />
               </p>
               <p> {error->Belt.Option.getWithDefault("")->React.string} </p>
             </label>
           }
         />
         {reform.state.formState == Submitting
            ? <p> {React.string("Saving...")} </p>
            : <button type_="submit"> {"Submit" |> React.string} </button>}
       </form>
     }}
  </PostAddForm.Provider>;
};
