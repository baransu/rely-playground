open Lwt_result.Infix;

exception Error;

let make_request = uri => {
  let req =
    Httpkit.Client.Request.create(
      ~headers=[("Content-Type", "application/json")],
      `GET,
      uri |> Uri.of_string,
    );

  Httpkit_lwt.Client.(req |> Http.send >>= Response.body |> Lwt_main.run);
};

let decode_result =
    (fn: string => Ppx_deriving_yojson_runtime.error_or('b), response)
    : ('b, string) => {
  switch (response) {
  | Result.Ok(body) =>
    let result = fn(body);
    switch (result) {
    | Result.Ok(response) => (response, body)
    | Result.Error(_) =>
      Console.error("\n\nDecode error");
      raise(Error);
    };
  | _ =>
    Console.error("\n\nRequest error");
    raise(Error);
  };
};
