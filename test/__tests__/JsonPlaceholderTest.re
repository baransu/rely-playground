open TestFramework;

[@deriving yojson]
type response = {
  userId: int,
  id: int,
  title: string,
  completed: bool,
};

describe("jsonplaceholder endpoint", ({describe, _}) =>
  describe("/todos", ({test, _}) =>
    test("returns single todo", ({expect, _}) => {
      let (response, raw_response) =
        "http://jsonplaceholder.typicode.com/todos/3"
        |> Utils.make_request
        |> Utils.decode_result(body =>
             body |> Yojson.Safe.from_string |> response_of_yojson
           );

      expect.string(raw_response).toMatchSnapshot();
      expect.equal(
        response,
        {id: 3, userId: 1, title: "fugiat veniam minus", completed: true},
      );
    })
  )
);
