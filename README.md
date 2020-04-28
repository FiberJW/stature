# Stature

<p align="center">
  <img src="./stat.jpg" width="256" />
</p>

## Get Started

Run `yarn add stature` and add `"stature"` to your BuckleScript dependencies list in `bsconfig.json`.

## Using the Library

```reason
open BsReactNative;

/* configuring your store */
module CounterConfig = {
  type t = int;
  let debugName = "Counter";
  let value = 0;
};

/* creating your store */
module CounterStore = Stature.CreateStore(CounterConfig);

/* accessing state in ui */
<CounterStore.Consumer
  render=(
    state =>
    <View>
      <Text>
        (ReasonReact.stringToElement(string_of_int(state)))
      </Text>
      <Button onPress=(() => CounterStore.updateState(Some(state + 1)) label="Increment Counter" />
    </View>
  )
/>

/* accessing state outside of a Consumer */
let oneUpped = CounterStore.state^ + 1;
```

## Using in ReasonReact

See the [example](./example/src/Example.re).

```re
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
    <CounterStore.Consumer
      render={state =>
          <h1> {React.string("Increment Counter")} </h1>
          <p> {React.string(string_of_int(state))} </p>
          <button style=leftButtonStyle onClick={_ => CounterStore.updateState(Some(state + 1))}>
            {React.string("+")}
          </button>
          <button style=rightButtonStyle onClick={_ => CounterStore.updateState(Some(state - 1))}>
            {React.string("-")}
          </button>
      }
    />
};
/* accessing state outside of a Consumer */
let oneUpped = CounterStore.state^ + 1;
Js.log2("OnUpped:accessing state outside of a Consumer",oneUpped);
```