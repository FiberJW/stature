let leftButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="4px 0px 0px 4px", ~width="48px", ());
let rightButtonStyle =
  ReactDOMRe.Style.make(~borderRadius="0px 4px 4px 0px", ~width="48px", ());
let containerStyle =
  ReactDOMRe.Style.make(
    ~display="flex",
    ~alignItems="center",
    ~justifyContent="space-between",
    (),
  );

module CounterConfig = {
  type t = int;
  let debugName = "Counter";
  let value = 0;
};

/* creating your store */
module CounterStore = Stature.CreateStore(CounterConfig);

/* accessing state in ui */
[@react.component]
let make = () => {
  <div style=containerStyle>
    <CounterStore.Consumer
      render={state =>
        <div>
          <h1> {React.string("Increment Counter")} </h1>
          <p> {React.string(string_of_int(state))} </p>
          <button style=leftButtonStyle onClick={_ => CounterStore.updateState(Some(state + 1))}>
            {React.string("+")}
          </button>
          <button style=rightButtonStyle onClick={_ => CounterStore.updateState(Some(state - 1))}>
            {React.string("-")}
          </button>
        </div>
      }
    />
  </div>;
};
/* accessing state outside of a Consumer */
let oneUpped = CounterStore.state^ + 1;
Js.log2("OnUpped:accessing state outside of a Consumer",oneUpped);