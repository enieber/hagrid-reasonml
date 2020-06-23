let logoImgUrl = Helpers.import("./logo.png");

[@react.component]
let make = () => {
  <header className="App-header">
    <div>
      <a href="/"> <img src=logoImgUrl className="App-logo" alt="logo" /> </a>
    </div>
    <nav className="App-header-nav">
      <a className="header-nav-link" href="/sobre"> "Itens"->React.string </a>
      <a className="header-nav-link" href="/sobre"> "Cofres"->React.string </a>
      <a className="header-nav-link" href="/sobre"> "Salas"->React.string </a>
      <a className="header-nav-link" href="/sobre">
        "Predios"->React.string
      </a>
      <a className="header-nav-link" href="/sobre">
        "Sobre o Projeto"->React.string
      </a>
    </nav>
  </header>;
};
