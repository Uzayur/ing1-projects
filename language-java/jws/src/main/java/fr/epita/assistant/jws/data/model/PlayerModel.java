package fr.epita.assistant.jws.data.model;


import lombok.*;
import net.bytebuddy.asm.Advice;

import javax.persistence.*;
import java.sql.Timestamp;
import java.time.LocalDateTime;

@Entity @With @AllArgsConstructor @NoArgsConstructor @ToString @Getter
@Table(name="player")
public class PlayerModel {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY) public Long id;
    @Column(name="lastbomb") public LocalDateTime lastBomb;
    @Column(name="lastmovement") public LocalDateTime lastMovement;
    @Column(name="lives") public Integer lives;
    @Column(name="name") public String name;
    @Column(name="posx") public Integer posX;
    @Column(name="posy") public Integer posY;
    @Column(name="position") public Long position;

    @ManyToOne public GameModel gameModel;
}
