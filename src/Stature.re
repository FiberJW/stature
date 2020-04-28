module type StoreConfig = {
  let debugName: string;
  /* the type of data in this Store */
  type t;
  /* The initial value of the Store */
  let value: t;
};

module CreateStore = (C: StoreConfig) => {
  type action =
    | ChangeState(C.t);
  let state = ref(C.value);
  let subscriptions = ref([||]);
  let addSubscription = f => {
    subscriptions := Js.Array.concat([|f|], subscriptions^);
    () => subscriptions := Js.Array.filter(sub => sub !== f, subscriptions^);
  };
  let updateState = newStateOpt => {
    let newState =
      switch (newStateOpt) {
      | None => C.value
      | Some(newValue) => newValue
      };
    state := newState;
    Js.Array.forEach(f => f(newState), subscriptions^);
  };
  module Consumer = {
    [@react.component]
    let make = (~render, ()) =>
      ReactCompat.useRecordApi({
        ...ReactCompat.component,

        initialState: () => state^,
        reducer: (action, _state) =>
          switch (action) {
          | ChangeState(newState) => Update(newState)
          },
        didMount: ({send, onUnmount}) =>
          (newState => send(ChangeState(newState)))
          |> addSubscription
          |> onUnmount,
        render: ({state}) => render(state),
      });
  };
};
