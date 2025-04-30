struct Player {
  var name: String
  init(name: String) {
    self.name = name
  }
}

struct Team {
  var players: (Player, Player)
}

var t1 = Team(players: (Player(name: "Jordi"), Player(name: "Pepe")))
var t2 = Team(players: (Player(name: "Santi"), Player(name: "Andreu")))

struct Match {
  var teams: (Team, Team)
}

var match = Match(teams: (t1, t2))
print("\(match.teams.0.players.0)")
