#!/usr/bin/perl
# guess_crud.pl
# Jogo de adivinhacao com CRUD simples (Perl).
use strict;
use warnings;
use Fcntl ':flock';

my $DATAFILE = "results.txt";

sub menu {
    while (1) {
        print "\n=== Jogo de Adivinhacao (Perl) ===\n";
        print "1) Jogar\n";
        print "2) Listar resultados\n";
        print "3) Remover resultado por id\n";
        print "4) Sair\n";
        print "Escolha: ";
        chomp(my $op = <STDIN>);
        if ($op eq '1') { play_game(); }
        elsif ($op eq '2') { list_results(); }
        elsif ($op eq '3') { remove_result(); }
        elsif ($op eq '4') { print "Tchau!\n"; last; }
        else { print "Opcao invalida.\n"; }
    }
}

sub play_game {
    print "Seu nome: ";
    chomp(my $player = <STDIN>);
    $player = "Anonimo" if $player eq '';

    print "Intervalo - minimo: ";
    chomp(my $min = <STDIN>);
    print "Intervalo - maximo: ";
    chomp(my $max = <STDIN>);
    ($min, $max) = ($max, $min) if $min > $max;

    srand(time ^ $$);
    my $target = $min + int(rand($max - $min + 1));
    my $attempts = 0;
    print "Ok $player! Pensei num numero entre $min e $max. Tente adivinhar.\n";
    while (1) {
        print "Seu palpite: ";
        chomp(my $g = <STDIN>);
        $attempts++;
        if ($g == $target) {
            print "Parabens! Voce acertou em $attempts tentativas.\n";
            last;
        } elsif ($g < $target) {
            print "Maior!\n";
        } else {
            print "Menor!\n";
        }
    }

    # Gravar resultado - lock para seguranca basica
    my $id = next_id();
    open(my $fh, '>>', $DATAFILE) or die "Nao foi possivel abrir $DATAFILE: $!";
    flock($fh, LOCK_EX);
    print $fh "$id|$player|$min|$max|$target|$attempts|ACERTOU\n";
    flock($fh, LOCK_UN);
    close $fh;
    print "Resultado salvo com id $id.\n";
}

sub list_results {
    if (!-e $DATAFILE) { print "Nenhum resultado ainda.\n"; return; }
    open my $fh, '<', $DATAFILE or die "Nao abriu: $!";
    print "\n--- Resultados salvos ---\n";
    print "ID | Jogador | Min | Max | Target | Tentativas | Status\n";
    while (my $l = <$fh>) {
        chomp $l;
        next if $l =~ /^\s*$/;
        $l =~ s/\|/ | /g;
        print "$l\n";
    }
    close $fh;
}

sub remove_result {
    print "Digite o id a remover: ";
    chomp(my $id = <STDIN>);
    if (!-e $DATAFILE) { print "Arquivo de resultados nao existe.\n"; return; }
    open my $in, '<', $DATAFILE or die $!;
    open my $out, '>', 'tmp_results.txt' or die $!;
    my $found = 0;
    while (my $l = <$in>) {
        my ($curid) = split(/\|/, $l);
        if ($curid == $id) { $found = 1; next; }
        print $out $l;
    }
    close $in; close $out;
    if (!$found) {
        unlink 'tmp_results.txt';
        print "ID $id nao encontrado.\n";
    } else {
        unlink $DATAFILE;
        rename 'tmp_results.txt', $DATAFILE or die "Erro ao renomear: $!";
        print "Registro $id removido.\n";
    }
}

sub next_id {
    return 1 unless -e $DATAFILE;
    open my $fh, '<', $DATAFILE or die $!;
    my $max = 0;
    while (my $l = <$fh>) {
        my ($id) = split(/\|/, $l);
        $max = $id if $id > $max;
    }
    close $fh;
    return $max + 1;
}

# start
menu();

