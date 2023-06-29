package fr.epita.assistant.jws.data.model;

import lombok.*;

import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.List;

@Entity @With @AllArgsConstructor @NoArgsConstructor @ToString @Getter
@Table(name = "game")
public class GameModel {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY) public Long id;
    @Column(name="starttime") public LocalDateTime startTime;
    public @Enumerated(EnumType.STRING) GameState state;

    public @ElementCollection @CollectionTable(name="map") List<String> map;

    @OneToMany public List<PlayerModel> listPlayers;
}